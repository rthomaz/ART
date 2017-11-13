﻿namespace ART.Domotica.Domain.Services
{
    using System.Collections.Generic;
    using System.Threading.Tasks;
    using ART.Domotica.Domain.Interfaces;
    using ART.Domotica.Repository.Interfaces;
    using ART.Domotica.Repository.Entities;
    using ART.Infra.CrossCutting.MQ.Contract;
    using ART.Domotica.Contract;
    using System;
    using ART.Infra.CrossCutting.Domain;
    using ART.Infra.CrossCutting.Utils;
    using System.Transactions;
    using global::AutoMapper;
    using Autofac;
    using ART.Domotica.Repository;
    using ART.Domotica.Repository.Repositories;

    public class ESPDeviceDomain : DomainBase, IESPDeviceDomain
    {
        #region Fields

        private readonly IESPDeviceRepository _espDeviceRepository;
        private readonly IDSFamilyTempSensorRepository _dsFamilyTempSensorRepository;
        private readonly IHardwareInApplicationRepository _hardwareInApplicationRepository;
        private readonly IApplicationUserRepository _applicationUserRepository;                

        #endregion Fields

        #region Constructors

        public ESPDeviceDomain(IComponentContext componentContext)
        {
            var context = componentContext.Resolve<ARTDbContext>();

            _espDeviceRepository = new ESPDeviceRepository(context);
            _dsFamilyTempSensorRepository = new DSFamilyTempSensorRepository(context);
            _applicationUserRepository = new ApplicationUserRepository(context);
            _hardwareInApplicationRepository = new HardwareInApplicationRepository(context);
        }

        #endregion Constructors

        #region Methods

        public async Task<List<ESPDeviceBase>> GetListInApplication(AuthenticatedMessageContract message)
        {
            var data = await _espDeviceRepository.GetListInApplication(message.ApplicationUserId);
            return Mapper.Map<List<ESPDeviceBase>, List<ESPDeviceBase>>(data);
        }

        public async Task<ESPDeviceBase> GetByPin(AuthenticatedMessageContract<ESPDeviceGetByPinRequestContract> message)
        {
            var data = await _espDeviceRepository.GetByPin(message.Contract.Pin);

            if (data == null)
            {
                throw new Exception("Pin not found");
            }

            return data;
        }

        public async Task<ESPDeviceBase> InsertInApplication(AuthenticatedMessageContract<ESPDeviceInsertInApplicationRequestContract> message)
        {
            var hardwareEntity = await _espDeviceRepository.GetByPin(message.Contract.Pin);

            if (hardwareEntity == null)
            {
                throw new Exception("Pin not found");
            }

            var applicationUserEntity = await _applicationUserRepository.GetById(message.ApplicationUserId);

            if (applicationUserEntity == null)
            {
                throw new Exception("ApplicationUser not found");
            }

            var entitiesToInsert = new List<HardwareInApplication>
            {
                new HardwareInApplication
                {
                    ApplicationId = applicationUserEntity.ApplicationId,
                    HardwareBaseId = hardwareEntity.Id,
                    CreateByApplicationUserId = applicationUserEntity.Id,
                    CreateDate = DateTime.Now.ToUniversalTime(),
                }
            };

            var allSensorsThatAreNotInApplication = await _dsFamilyTempSensorRepository.GetAllThatAreNotInApplicationByDevice(hardwareEntity.Id);

            foreach (var item in allSensorsThatAreNotInApplication)
            {
                entitiesToInsert.Add(new HardwareInApplication
                {
                    ApplicationId = applicationUserEntity.ApplicationId,
                    HardwareBaseId = item.Id,
                    CreateByApplicationUserId = applicationUserEntity.Id,
                    CreateDate = DateTime.Now.ToUniversalTime(),
                });                
            }

            using (var scope = new TransactionScope(TransactionScopeAsyncFlowOption.Enabled))
            {
                await _hardwareInApplicationRepository.Insert(entitiesToInsert);
                scope.Complete();
            }

            return hardwareEntity;
        }

        public async Task<ESPDeviceBase> DeleteFromApplication(AuthenticatedMessageContract<ESPDeviceDeleteFromApplicationRequestContract> message)
        {
            var hardwareInApplicationEntity = await _hardwareInApplicationRepository.GetById(message.Contract.HardwareInApplicationId);
            
            if (hardwareInApplicationEntity == null)
            {
                throw new Exception("HardwareInApplication not found");
            }

            await _hardwareInApplicationRepository.Delete(hardwareInApplicationEntity);

            var hardwareEntity = await _espDeviceRepository.GetById(hardwareInApplicationEntity.HardwareBaseId);

            return hardwareEntity;
        }

        public async Task<List<ESPDeviceBase>> UpdatePins()
        {
            var existingPins = await _espDeviceRepository.GetExistingPins();
            var entities = await _espDeviceRepository.GetListNotInApplication();

            foreach (var item in entities)
            {
                var pin = RandonHelper.RandomString(4);
                while (existingPins.Contains(pin))
                {
                    pin = RandonHelper.RandomString(4);
                }
                item.Pin = pin;
            }

            using (var scope = new TransactionScope(TransactionScopeAsyncFlowOption.Enabled))
            {
                await _espDeviceRepository.Update(entities);
                scope.Complete();
            }

            return entities;
        }

        public async Task<ESPDeviceBase> GetConfigurations(ESPDeviceGetConfigurationsRPCRequestContract contract)
        {
            var data = await _espDeviceRepository.GetDeviceInApplication(contract.ChipId, contract.FlashChipId, contract.MacAddress);            

            if (data == null)
            {
                throw new Exception("ESP Device not found");
            }

            return data;
        }

        #endregion Methods
    }
}
﻿namespace ART.Domotica.Repository.Interfaces
{
    using System.Collections.Generic;
    using System.Threading.Tasks;

    using ART.Domotica.Enums;
    using ART.Domotica.Repository.Entities;

    public interface IUnitOfMeasurementRepository
    {
        #region Methods

        Task<List<UnitOfMeasurement>> GetAll();

        Task<UnitOfMeasurement> GetByKey(UnitOfMeasurementEnum unitOfMeasurementId, UnitOfMeasurementTypeEnum unitOfMeasurementTypeId);

        #endregion Methods
    }
}
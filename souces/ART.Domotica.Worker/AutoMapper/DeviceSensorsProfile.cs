﻿namespace ART.Domotica.Worker.AutoMapper
{
    using System.Linq;

    using ART.Domotica.IoTContract;
    using ART.Domotica.Model;
    using ART.Domotica.Repository.Entities;

    using global::AutoMapper;

    public class DeviceSensorsProfile : Profile
    {
        #region Constructors

        public DeviceSensorsProfile()
        {
            CreateMap<DeviceSensors, DeviceSensorsGetModel>()
                .ForMember(vm => vm.DeviceTypeId, m => m.MapFrom(x => x.DeviceTypeId))
                .ForMember(vm => vm.DeviceDatasheetId, m => m.MapFrom(x => x.DeviceDatasheetId))
                .ForMember(vm => vm.DeviceId, m => m.MapFrom(x => x.Id))
                .ForMember(vm => vm.ReadIntervalInMilliSeconds, m => m.MapFrom(x => x.ReadIntervalInMilliSeconds))
                .ForMember(vm => vm.PublishIntervalInMilliSeconds, m => m.MapFrom(x => x.PublishIntervalInMilliSeconds))
                .ForMember(vm => vm.SensorInDevice, m => m.MapFrom(x => x.SensorInDevice.OrderBy(y => y.Ordination)));

            CreateMap<DeviceSensors, DeviceSensorsSetReadIntervalInMilliSecondsModel>()
                .ForMember(vm => vm.DeviceTypeId, m => m.MapFrom(x => x.DeviceTypeId))
                .ForMember(vm => vm.DeviceDatasheetId, m => m.MapFrom(x => x.DeviceDatasheetId))
                .ForMember(vm => vm.DeviceId, m => m.MapFrom(x => x.Id))
                .ForMember(vm => vm.ReadIntervalInMilliSeconds, m => m.MapFrom(x => x.ReadIntervalInMilliSeconds));

            CreateMap<DeviceSensors, DeviceSetPublishIntervalInMilliSecondsModel>()
                .ForMember(vm => vm.DeviceTypeId, m => m.MapFrom(x => x.DeviceTypeId))
                .ForMember(vm => vm.DeviceDatasheetId, m => m.MapFrom(x => x.DeviceDatasheetId))
                .ForMember(vm => vm.DeviceId, m => m.MapFrom(x => x.Id))
                .ForMember(vm => vm.PublishIntervalInMilliSeconds, m => m.MapFrom(x => x.PublishIntervalInMilliSeconds));

            CreateMap<DeviceSensors, DeviceSensorsGetResponseIoTContract>()
                .ForMember(vm => vm.SensorsInDevice, m => m.MapFrom(x => x.SensorInDevice.OrderBy(y => y.Ordination)))
                .ForMember(vm => vm.ReadIntervalInMilliSeconds, m => m.MapFrom(x => x.ReadIntervalInMilliSeconds))
                .ForMember(vm => vm.PublishIntervalInMilliSeconds, m => m.MapFrom(x => x.PublishIntervalInMilliSeconds))
                .ForMember(vm => vm.SensorDatasheets, m => m.MapFrom(x => x.SensorInDevice.Select(y => y.Sensor.SensorDatasheet).Distinct()));
        }

        #endregion Constructors
    }
}
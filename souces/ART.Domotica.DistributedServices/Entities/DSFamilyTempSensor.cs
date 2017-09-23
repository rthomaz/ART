﻿namespace ART.Domotica.DistributedServices.Entities
{
    public class DSFamilyTempSensor : SensorBase
    {
        #region Primitive Properties

        public string DeviceAddress { get; set; }
        public string Family { get; set; }
        public byte Resolution { get; set; }

        #endregion

        #region Navigation Properties


        #endregion        
    }
}
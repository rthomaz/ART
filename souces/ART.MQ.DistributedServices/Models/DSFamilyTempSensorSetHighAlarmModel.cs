﻿namespace ART.MQ.DistributedServices.Models
{
    using System;

    public class DSFamilyTempSensorSetHighAlarmModel
    {
        #region Properties

        public Guid DSFamilyTempSensorId
        {
            get; set;
        }

        public decimal HighAlarm
        {
            get; set;
        }

        #endregion Properties
    }
}
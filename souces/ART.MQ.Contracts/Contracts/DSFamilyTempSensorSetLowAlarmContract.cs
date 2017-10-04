﻿namespace ART.MQ.Common.Contracts
{
    using System;

    [Serializable]
    public class DSFamilyTempSensorSetLowAlarmContract
    {
        #region Properties

        public Guid DSFamilyTempSensorId
        {
            get; set;
        }

        public decimal LowAlarm
        {
            get; set;
        }

        #endregion Properties
    }
}
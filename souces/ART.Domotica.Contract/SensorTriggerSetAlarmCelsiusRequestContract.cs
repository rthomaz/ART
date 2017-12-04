﻿namespace ART.Domotica.Contract
{
    using System;

    using ART.Domotica.Enums;

    public class SensorTriggerSetAlarmCelsiusRequestContract
    {
        #region Properties

        public decimal AlarmCelsius
        {
            get; set;
        }

        public Guid DSFamilyTempSensorId
        {
            get; set;
        }

        public SensorUnitMeasurementScalePositionEnum Position
        {
            get; set;
        }

        #endregion Properties
    }
}
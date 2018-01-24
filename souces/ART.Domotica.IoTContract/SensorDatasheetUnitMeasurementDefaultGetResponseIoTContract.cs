﻿namespace ART.Domotica.IoTContract
{
    using ART.Domotica.Enums;

    public class SensorDatasheetUnitMeasurementDefaultGetResponseIoTContract
    {
        #region Properties

        public SensorDatasheetEnum SensorDatasheetId
        {
            get; set;
        }

        public SensorTypeEnum SensorTypeId
        {
            get; set;
        }

        #endregion Properties
    }
}
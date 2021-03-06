﻿namespace ART.Domotica.Model
{
    using ART.Domotica.Enums;

    public class SensorDatasheetGetModel
    {
        #region Properties

        public string Name
        {
            get; set;
        }

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
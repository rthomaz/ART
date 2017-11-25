﻿namespace ART.Domotica.Contract
{
    public class DeviceNTPDetailResponseContract
    {
        #region Properties

        public string Host
        {
            get; set;
        }

        public int Port
        {
            get; set;
        }

        public int UtcTimeOffsetInSecond
        {
            get; set;
        }

        public int UpdateIntervalInMilliSecond
        {
            get; set;
        }

        #endregion Properties
    }
}
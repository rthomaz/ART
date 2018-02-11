﻿namespace ART.Domotica.IoTContract
{
    using ART.Domotica.Enums;
    using System;

    public class DeviceSerialGetResponseIoTContract
    {
        #region Properties

        public bool AllowPinSwapRX
        {
            get; set;
        }

        public bool AllowPinSwapTX
        {
            get; set;
        }

        public Guid DeviceSerialId
        {
            get; set;
        }

        public bool Enabled
        {
            get; set;
        }

        public SerialModeEnum SerialMode
        {
            get; set;
        }

        public short Index
        {
            get; set;
        }

        public short PinRX
        {
            get; set;
        }

        public short PinTX
        {
            get; set;
        }

        #endregion Properties
    }
}
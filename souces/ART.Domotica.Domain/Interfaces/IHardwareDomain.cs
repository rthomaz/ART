﻿namespace ART.Domotica.Domain.Interfaces
{
    using System.Collections.Generic;
    using System.Threading.Tasks;

    using ART.Domotica.Contract;

    public interface IHardwareDomain
    {
        #region Methods

        Task<List<HardwareUpdatePinsContract>> UpdatePins();

        #endregion Methods
    }
}
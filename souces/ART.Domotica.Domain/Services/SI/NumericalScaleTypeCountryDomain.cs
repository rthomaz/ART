﻿using System.Threading.Tasks;
using System.Collections.Generic;
using ART.Infra.CrossCutting.Domain;
using ART.Domotica.Repository.Entities.SI;
using ART.Domotica.Repository.Interfaces.SI;
using ART.Domotica.Domain.Interfaces.SI;
using Autofac;
using ART.Domotica.Repository;
using ART.Domotica.Repository.Repositories.SI;

namespace ART.Domotica.Domain.Services.SI
{
    public class NumericalScaleTypeCountryDomain : DomainBase, INumericalScaleTypeCountryDomain
    {
        #region private readonly fields

        private readonly INumericalScaleTypeCountryRepository _numericalScaleTypeCountryRepository;

        #endregion

        #region constructors

        public NumericalScaleTypeCountryDomain(IComponentContext componentContext)
        {
            var context = componentContext.Resolve<ARTDbContext>();

            _numericalScaleTypeCountryRepository = new NumericalScaleTypeCountryRepository(context);
        }

        #endregion

        #region public voids

        public async Task<List<NumericalScaleTypeCountry>> GetAll()
        {
            return await _numericalScaleTypeCountryRepository.GetAll();
        }

        #endregion
    }
}

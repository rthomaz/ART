﻿'use strict';
app.factory('siMapper', ['$rootScope', 'siContext', 'localeContext', function ($rootScope, siContext, localeContext) {

    var serviceFactory = {};    

    // *** Navigation Properties Mappers ***

    var mapper_NumericalScaleTypeCountry_Init = false;
    var mapper_NumericalScaleTypeCountry = function () {
        if (!mapper_NumericalScaleTypeCountry_Init && siContext.numericalScaleTypeCountryLoaded && localeContext.countryLoaded) {
            mapper_NumericalScaleTypeCountry_Init = true;
            for (var i = 0; i < siContext.numericalScaleTypeCountries.length; i++) {
                var numericalScaleTypeCountry = siContext.numericalScaleTypeCountries[i];
                var numericalScaleType = siContext.getNumericalScaleTypeByKey(numericalScaleTypeCountry.numericalScaleTypeId);
                var country = localeContext.getCountryByKey(numericalScaleTypeCountry.countryId);
                //Atach in numericalScaleType
                if (numericalScaleType.countries === undefined) {
                    numericalScaleType.countries = [];
                }
                numericalScaleType.countries.push(country);
                //Atach in country
                if (country.numericalScaleTypes === undefined) {
                    country.numericalScaleTypes = [];
                }
                country.numericalScaleTypes.push(numericalScaleType);
            }
            delete siContext.numericalScaleTypeCountries;
            delete siContext.numericalScaleTypeCountryLoaded;
        }
    };

    var mapper_NumericalScale_NumericalScalePrefix_Init = false;
    var mapper_NumericalScale_NumericalScalePrefix = function () {
        if (!mapper_NumericalScale_NumericalScalePrefix_Init && siContext.numericalScaleLoaded && siContext.numericalScalePrefixLoaded) {
            mapper_NumericalScale_NumericalScalePrefix_Init = true;
            for (var i = 0; i < siContext.numericalScales.length; i++) {
                var numericalScale = siContext.numericalScales[i];
                var numericalScalePrefix = siContext.getNumericalScalePrefixByKey(numericalScale.numericalScalePrefixId);
                numericalScale.numericalScalePrefix = numericalScalePrefix;
                if (numericalScalePrefix.numericalScales === undefined) {
                    numericalScalePrefix.numericalScales = [];
                }
                numericalScalePrefix.numericalScales.push(numericalScale);
            }
        }
    };

    var mapper_NumericalScale_NumericalScaleType_Init = false;
    var mapper_NumericalScale_NumericalScaleType = function () {
        if (!mapper_NumericalScale_NumericalScaleType_Init && siContext.numericalScaleLoaded && siContext.numericalScaleTypeLoaded) {
            mapper_NumericalScale_NumericalScaleType_Init = true;
            for (var i = 0; i < siContext.numericalScales.length; i++) {
                var numericalScale = siContext.numericalScales[i];
                var numericalScaleType = siContext.getNumericalScaleTypeByKey(numericalScale.numericalScaleTypeId);
                numericalScale.numericalScaleType = numericalScaleType;
                if (numericalScaleType.numericalScales === undefined) {
                    numericalScaleType.numericalScales = [];
                }
                numericalScaleType.numericalScales.push(numericalScale);
            }
        }
    };

    var mapper_UnitMeasurement_UnitMeasurementType_Init = false;
    var mapper_UnitMeasurement_UnitMeasurementType = function () {
        if (!mapper_UnitMeasurement_UnitMeasurementType_Init && siContext.unitMeasurementTypeLoaded && siContext.unitMeasurementLoaded) {
            mapper_UnitMeasurement_UnitMeasurementType_Init = true;
            for (var i = 0; i < siContext.unitMeasurements.length; i++) {
                var unitMeasurement = siContext.unitMeasurements[i];
                var unitMeasurementType = siContext.getUnitMeasurementTypeByKey(unitMeasurement.unitMeasurementTypeId);
                unitMeasurement.unitMeasurementType = unitMeasurementType;
                if (unitMeasurementType.unitMeasurements === undefined) {
                    unitMeasurementType.unitMeasurements = [];
                }
                unitMeasurementType.unitMeasurements.push(unitMeasurement);
            }
        }
    };

    var mapper_UnitMeasurementScale_UnitMeasurement_Init = false;
    var mapper_UnitMeasurementScale_UnitMeasurement = function () {
        if (!mapper_UnitMeasurementScale_UnitMeasurement_Init && siContext.unitMeasurementScaleLoaded && siContext.unitMeasurementLoaded) {
            mapper_UnitMeasurementScale_UnitMeasurement_Init = true;
            for (var i = 0; i < siContext.unitMeasurementScales.length; i++) {
                var unitMeasurementScale = siContext.unitMeasurementScales[i];
                var unitMeasurement = siContext.getUnitMeasurementByKey(unitMeasurementScale.unitMeasurementId, unitMeasurementScale.unitMeasurementTypeId);
                unitMeasurementScale.unitMeasurement = unitMeasurement;
                if (unitMeasurement.unitMeasurementScales === undefined) {
                    unitMeasurement.unitMeasurementScales = [];
                }
                unitMeasurement.unitMeasurementScales.push(unitMeasurementScale);
            }
        }
    };

    var mapper_UnitMeasurementScale_NumericalScale_Init = false;
    var mapper_UnitMeasurementScale_NumericalScale = function () {
        if (!mapper_UnitMeasurementScale_NumericalScale_Init && siContext.unitMeasurementScaleLoaded && siContext.numericalScaleLoaded) {
            mapper_UnitMeasurementScale_NumericalScale_Init = true;
            for (var i = 0; i < siContext.unitMeasurementScales.length; i++) {
                var unitMeasurementScale = siContext.unitMeasurementScales[i];
                var numericalScale = siContext.getNumericalScaleByKey(unitMeasurementScale.numericalScalePrefixId, unitMeasurementScale.numericalScaleTypeId);
                unitMeasurementScale.numericalScale = numericalScale;
                if (numericalScale.unitMeasurementScales === undefined) {
                    numericalScale.unitMeasurementScales = [];
                }
                numericalScale.unitMeasurementScales.push(unitMeasurementScale);
            }
        }
    }; 

    // *** Watches ***

    // Locale   

    localeContext.$watch('countryLoaded', function (newValue, oldValue) {
        mapper_NumericalScaleTypeCountry();
    });

    // SI

    siContext.$watch('numericalScaleLoaded', function (newValue, oldValue) {
        mapper_NumericalScale_NumericalScalePrefix();
        mapper_NumericalScale_NumericalScaleType();
        mapper_UnitMeasurementScale_NumericalScale();
    });

    siContext.$watch('numericalScalePrefixLoaded', function (newValue, oldValue) {
        mapper_NumericalScale_NumericalScalePrefix();
    });

    siContext.$watch('numericalScaleTypeLoaded', function (newValue, oldValue) {
        mapper_NumericalScaleTypeCountry();
        mapper_NumericalScale_NumericalScaleType();
    });

    siContext.$watch('numericalScaleTypeCountryLoaded', function (newValue, oldValue) {
        mapper_NumericalScaleTypeCountry();
    });

    siContext.$watch('unitMeasurementScaleLoaded', function (newValue, oldValue) {
        mapper_UnitMeasurementScale_UnitMeasurement();
        mapper_UnitMeasurementScale_NumericalScale();
    });     

    siContext.$watch('unitMeasurementTypeLoaded', function (newValue, oldValue) {
        mapper_UnitMeasurement_UnitMeasurementType();
    });

    siContext.$watch('unitMeasurementLoaded', function (newValue, oldValue) {
        mapper_UnitMeasurement_UnitMeasurementType();
        mapper_UnitMeasurementScale_UnitMeasurement();
    });    

    return serviceFactory;

}]);
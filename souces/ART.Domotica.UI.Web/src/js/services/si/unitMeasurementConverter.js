﻿'use strict';
app.factory('unitMeasurementConverter', function () {

    var serviceFactory = {};    

    // To

    var convertToCelsius = function (unitMeasurementId, temperature) {
        switch (unitMeasurementId) {
            case 101:
                return parseFloat(temperature.toFixed(4));
            case 102:
                return convertFahrenheitToCelsius(temperature);
            default:
        }
    };

    var convertFahrenheitToCelsius = function (fahrenheit) {
        var result = (fahrenheit - 32) * (5 / 9);
        return parseFloat(result.toFixed(4));
    }       

    // From

    var convertFromCelsius = function (unitMeasurementId, celsius) {
        switch (unitMeasurementId) {
            case 101:
                return parseFloat(parseFloat(celsius).toFixed(4));
            case 102:
                return convertCelsiusToFahrenheit(celsius);
            default:
        }
    };       

    var convertCelsiusToFahrenheit = function (celsius) {
        var result = (celsius * 1.8) + 32;
        return parseFloat(result.toFixed(4));
    }

    // To

    serviceFactory.convertToCelsius = convertToCelsius;
    serviceFactory.convertFahrenheitToCelsius = convertFahrenheitToCelsius;

    // From

    serviceFactory.convertFromCelsius = convertFromCelsius;
    serviceFactory.convertCelsiusToFahrenheit = convertCelsiusToFahrenheit;
        
    return serviceFactory;

});
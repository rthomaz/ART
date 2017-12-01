﻿'use strict';
app.factory('sensorChartLimiterService', ['$http', '$log', '$rootScope', 'ngAuthSettings', 'stompService', 'unitMeasurementConverter', 'dsFamilyTempSensorService', function ($http, $log, $rootScope, ngAuthSettings, stompService, unitMeasurementConverter, dsFamilyTempSensorService) {

    var serviceBase = ngAuthSettings.distributedServicesUri;

    var initialized = false;

    var serviceFactory = {};   

    var setValue = function (sensorChartLimiterId, value, position) {
        var data = {
            sensorChartLimiterId: sensorChartLimiterId,
            value: value,
            position: position,
        }
        return $http.post(serviceBase + 'api/sensorChartLimiter/setValue', data).then(function (results) {
            return results;
        });
    };

    var onConnected = function () {
                
        stompService.subscribeAllViews('SensorChartLimiter.SetValueViewCompleted', onSetValueCompleted);

        if (!initialized) {
            initialized = true;            
        }
    }  

    var onSetValueCompleted = function (payload) {
        var result = JSON.parse(payload.body);
        var sensor = dsFamilyTempSensorService.getById(result.deviceId, result.sensorChartLimiterId);
        if (result.position === 'Max') {
            sensor.sensorChartLimiter.max = result.value;
            sensor.sensorChartLimiter.maxConverted = unitMeasurementConverter.convertFromCelsius(sensor.unitMeasurementId, sensor.sensorChartLimiter.max);            
        }
        else if (result.position === 'Min') {
            sensor.sensorChartLimiter.min = result.value;
            sensor.sensorChartLimiter.minConverted = unitMeasurementConverter.convertFromCelsius(sensor.unitMeasurementId, sensor.sensorChartLimiter.min);
        }
        $rootScope.$emit('sensorChartLimiterService_SetValueCompleted_Id_' + result.sensorChartLimiterId, result);
    }

    $rootScope.$on('$destroy', function () {
        clearOnConnected();
    });

    var clearOnConnected = $rootScope.$on('stompService_onConnected', onConnected); 

    // stompService
    if (stompService.connected())
        onConnected();

    // serviceFactory

    serviceFactory.setValue = setValue;    

    return serviceFactory;

}]);
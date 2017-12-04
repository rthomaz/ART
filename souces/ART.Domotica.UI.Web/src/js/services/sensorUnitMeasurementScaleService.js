﻿'use strict';
app.factory('sensorUnitMeasurementScaleService', ['$http', '$log', '$rootScope', 'ngAuthSettings', 'stompService', 'unitMeasurementConverter', 'dsFamilyTempSensorService', function ($http, $log, $rootScope, ngAuthSettings, stompService, unitMeasurementConverter, dsFamilyTempSensorService) {

    var serviceBase = ngAuthSettings.distributedServicesUri;

    var initialized = false;

    var serviceFactory = {};   

    var setValue = function (sensorUnitMeasurementScaleId, value, position) {
        var data = {
            sensorUnitMeasurementScaleId: sensorUnitMeasurementScaleId,
            value: value,
            position: position,
        }
        return $http.post(serviceBase + 'api/sensorUnitMeasurementScale/setValue', data).then(function (results) {
            return results;
        });
    };

    var onConnected = function () {
                
        stompService.subscribeAllViews('SensorUnitMeasurementScale.SetValueViewCompleted', onSetValueCompleted);

        if (!initialized) {
            initialized = true;            
        }
    }  

    var onSetValueCompleted = function (payload) {
        var result = JSON.parse(payload.body);
        var sensor = dsFamilyTempSensorService.getById(result.deviceId, result.sensorUnitMeasurementScaleId);
        if (result.position === 'Max') {
            sensor.sensorUnitMeasurementScale.max = result.value;
            sensor.sensorUnitMeasurementScale.maxConverted = unitMeasurementConverter.convertFromCelsius(sensor.unitMeasurementId, sensor.sensorUnitMeasurementScale.max);            
        }
        else if (result.position === 'Min') {
            sensor.sensorUnitMeasurementScale.min = result.value;
            sensor.sensorUnitMeasurementScale.minConverted = unitMeasurementConverter.convertFromCelsius(sensor.unitMeasurementId, sensor.sensorUnitMeasurementScale.min);
        }
        $rootScope.$emit('sensorUnitMeasurementScaleService_SetValueCompleted_Id_' + result.sensorUnitMeasurementScaleId, result);
    }

    $rootScope.$on('$destroy', function () {
        clearOnConnected();
    });

    var clearOnConnected = $rootScope.$on('stompService_onConnected', onConnected); 

    // stompService
    if (stompService.connected()) onConnected();

    // serviceFactory

    serviceFactory.setValue = setValue;    

    return serviceFactory;

}]);
﻿'use strict';
app.factory('sensorInDeviceService', ['$http', 'ngAuthSettings', '$rootScope', 'stompService', 'deviceContext', 'sensorInDeviceConstant', 'deviceSensorFinder', 'sensorInDeviceFinder',
    function ($http, ngAuthSettings, $rootScope, stompService, deviceContext, sensorInDeviceConstant, deviceSensorFinder, sensorInDeviceFinder) {

        var serviceFactory = {};

        var serviceBase = ngAuthSettings.distributedServicesUri;

        var setOrdinationCompletedSubscription = null;

        var setOrdination = function (deviceTypeId, deviceDatasheetId, deviceId, sensorId, sensorDatasheetId, sensorTypeId, ordination) {
            var data = {
                deviceTypeId: deviceTypeId,
                deviceDatasheetId: deviceDatasheetId,
                deviceId: deviceId,
                sensorId: sensorId,
                sensorDatasheetId: sensorDatasheetId,
                sensorTypeId: sensorTypeId,
                ordination: ordination,
            }
            return $http.post(serviceBase + sensorInDeviceConstant.setOrdinationApiUri, data).then(function (results) {
                return results;
            });
        };

        var onConnected = function () {
            setOrdinationCompletedSubscription = stompService.subscribeAllViews(sensorInDeviceConstant.setOrdinationCompletedTopic, onSetOrdinationCompleted);
        }

        var onSetOrdinationCompleted = function (payload) {
            var result = JSON.parse(payload.body);
            var deviceSensor = deviceSensorFinder.getByKey(result.deviceTypeId, result.deviceDatasheetId, result.deviceId);
            var sensorInDevice = sensorInDeviceFinder.getByKey(result.deviceTypeId, result.deviceDatasheetId, result.deviceId, result.sensorId, result.sensorDatasheetId, result.sensorTypeId);
            for (var i = 0; i < deviceSensor.sensorInDevice.length; i++) {
                if (sensorInDevice === deviceSensor.sensorInDevice[i]) {
                    deviceSensor.sensorInDevice.splice(i, 1);
                    break;
                }
            }
            deviceSensor.sensorInDevice.insert(result.ordination, sensorInDevice);
            deviceContext.$digest();
            $rootScope.$emit(sensorInDeviceConstant.setOrdinationCompletedEventName + result.deviceId, result);
        };

        $rootScope.$on('$destroy', function () {
            clearOnConnected();
            setOrdinationCompletedSubscription.unsubscribe();
        });

        var clearOnConnected = $rootScope.$on(stompService.connectedEventName, onConnected);

        // stompService
        if (stompService.connected()) onConnected();

        // serviceFactory

        serviceFactory.setOrdination = setOrdination;

        return serviceFactory;

    }]);


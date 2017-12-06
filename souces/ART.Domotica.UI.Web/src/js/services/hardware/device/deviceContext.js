﻿'use strict';
app.factory('deviceContext', ['$rootScope', function ($rootScope) {

    var context = $rootScope.$new();

    // *** Public Properties ***       
    
    context.deviceLoaded = false;

    context.device = [];   
    context.deviceNTP = [];   
    context.deviceSensors = [];   
    context.sensorsInDevice = [];   

    context.timeZoneLoaded = false;
    context.timeZone = [];
        
    // *** Finders ***        

    var getDeviceByKey = function (deviceId) {
        for (var i = 0; i < context.devices.length; i++) {
            var item = context.devices[i];
            if (item.deviceId === deviceId) {
                return item;
            }
        }
    }; 

    var getDeviceNTPByKey = function (deviceNTPId) {
        for (var i = 0; i < context.deviceNTPs.length; i++) {
            var item = context.deviceNTPs[i];
            if (item.deviceNTPId === deviceNTPId) {
                return item;
            }
        }
    }; 


    var getDeviceSensorsByKey = function (deviceSensorsId) {
        for (var i = 0; i < context.deviceSensors.length; i++) {
            var item = context.deviceSensors[i];
            if (item.deviceSensorsId === deviceSensorsId) {
                return item;
            }
        }
    }; 

    var getDeviceSensorsByKey = function (sensorsInDeviceId) {
        for (var i = 0; i < context.sensorsInDevices.length; i++) {
            var item = context.sensorsInDevices[i];
            if (item.sensorsInDeviceId === sensorsInDeviceId) {
                return item;
            }
        }
    };     

    var getTimeZoneByKey = function (timeZoneId) {
        for (var i = 0; i < context.timeZone.length; i++) {
            var item = context.timeZone[i];
            if (item.timeZoneId === timeZoneId) {
                return item;
            }
        }
    }

    // *** Public Methods ***

    context.getDeviceByKey = getDeviceByKey;
    context.getDeviceNTPByKey = getDeviceNTPByKey;
    context.getDeviceSensorsByKey = getDeviceSensorsByKey;
    context.getDeviceSensorsByKey = getDeviceSensorsByKey;

    context.getTimeZoneByKey = getTimeZoneByKey;

    return context;

}]);
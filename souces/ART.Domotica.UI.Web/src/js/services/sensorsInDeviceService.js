﻿'use strict';
app.factory('sensorsInDeviceService', ['$http', 'ngAuthSettings', '$rootScope', 'stompService', 'contextScope', function ($http, ngAuthSettings, $rootScope, stompService, contextScope) {

    var serviceBase = ngAuthSettings.distributedServicesUri;

    var serviceFactory = {};

    var _initializing = false;
    var _initialized = false;

    var getAllByApplicationIdApiUri = 'api/sensorsInDevice/getAllByApplicationId';
    var getAllByApplicationIdCompletedTopic = 'SensorsInDevice.GetAllByApplicationIdViewCompleted';
    var getAllByApplicationIdCompletedSubscription = null;

    var initializedEventName = 'sensorsInDeviceService.onInitialized';

    var onConnected = function () {

        getAllByApplicationIdCompletedSubscription = stompService.subscribe(getAllByApplicationIdCompletedTopic, onGetAllByApplicationIdCompleted);

        if (!_initializing && !_initialized) {
            _initializing = true;
            getAllByApplicationId();
        }
    }

    var initialized = function () {
        return _initialized;
    };

    var getAllByApplicationId = function () {
        return $http.post(serviceBase + getAllByApplicationIdApiUri).then(function (results) {
            //alert('envio bem sucedido');
        });
    };

    var onGetAllByApplicationIdCompleted = function (payload) {

        var dataUTF8 = decodeURIComponent(escape(payload.body));
        var data = JSON.parse(dataUTF8);

        for (var i = 0; i < data.length; i++) {
            contextScope.sensorsInDevice.push(data[i]);
        }

        _initializing = false;
        _initialized = true;

        contextScope.sensorsInDeviceLoaded = true;
        clearOnConnected();

        getAllByApplicationIdCompletedSubscription.unsubscribe();

        $rootScope.$emit(initializedEventName);
    }

    $rootScope.$on('$destroy', function () {
        clearOnConnected();
    });

    var clearOnConnected = $rootScope.$on(stompService.connectedEventName, onConnected);

    // stompService
    if (stompService.connected()) onConnected();

    // serviceFactory

    serviceFactory.initialized = initialized;
    serviceFactory.initializedEventName = initializedEventName;

    return serviceFactory;

}]);
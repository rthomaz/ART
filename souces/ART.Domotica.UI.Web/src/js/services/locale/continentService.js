﻿'use strict';

app.constant('continentConstant', {
    getAllApiUri: 'api/locale/continent/getAll',
    getAllCompletedTopic: 'Locale.Continent.GetAllViewCompleted',
    initializedEventName: 'continentService.onInitialized',
});


app.factory('continentService', ['$http', 'ngAuthSettings', 'continentConstant', '$rootScope', 'stompService', 'localeContext', function ($http, ngAuthSettings, continentConstant, $rootScope, stompService, localeContext) {

    var serviceFactory = {};    

    var serviceBase = ngAuthSettings.distributedServicesUri;

    var _initializing = false;
    var _initialized  = false;

    var getAllCompletedSubscription = null;
    
    var onConnected = function () {

        getAllCompletedSubscription = stompService.subscribe(continentConstant.getAllCompletedTopic, onGetAllCompleted);

        if (!_initializing && !_initialized) {
            _initializing = true;
            getAll();
        }
    }   

    var initialized = function () {
        return _initialized;
    };

    var getAll = function () {
        return $http.post(serviceBase + continentConstant.getAllApiUri).then(function (results) {
            //alert('envio bem sucedido');
        });
    };       

    var onGetAllCompleted = function (payload) {

        var dataUTF8 = decodeURIComponent(escape(payload.body));
        var data = JSON.parse(dataUTF8);

        for (var i = 0; i < data.length; i++) {
            localeContext.continents.push(data[i]);
        }
        
        _initializing = false;
        _initialized = true;

        localeContext.continentLoaded = true;
        clearOnConnected();

        getAllCompletedSubscription.unsubscribe();

        $rootScope.$emit(continentConstant.initializedEventName);
    }

    $rootScope.$on('$destroy', function () {
        clearOnConnected();
    });

    var clearOnConnected = $rootScope.$on(stompService.connectedEventName, onConnected);       

    // stompService
    if (stompService.connected()) onConnected();

    // serviceFactory

    serviceFactory.initialized = initialized;

    return serviceFactory;

}]);
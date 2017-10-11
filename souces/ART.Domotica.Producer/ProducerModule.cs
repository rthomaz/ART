﻿namespace ART.Domotica.Producer
{
    using ART.Infra.CrossCutting.Logging;
    using Autofac;
    using Autofac.Extras.DynamicProxy;
    using System.Reflection;

    public class ProducerModule : Autofac.Module
    {
        #region Methods

        protected override void Load(ContainerBuilder builder)
        {
            var asm = Assembly.GetExecutingAssembly();

            builder.RegisterAssemblyTypes(asm)
                .Where(x => x.Name.EndsWith("Producer"))
                .AsImplementedInterfaces()
                .EnableInterfaceInterceptors()
                .InterceptedBy(typeof(CallDebugLogger));
        }

        #endregion Methods
    }
}
﻿namespace ART.Domotica.Repository.Configurations
{
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Infrastructure.Annotations;
    using System.Data.Entity.ModelConfiguration;

    using ART.Domotica.Repository.Entities;

    public class DeviceMQConfiguration : EntityTypeConfiguration<DeviceMQ>
    {
        #region Constructors

        public DeviceMQConfiguration()
        {
            //Primary Keys
            HasKey(x => new
            {
                x.DeviceTypeId,
                x.DeviceDatasheetId,
                x.Id,
            });

            //DeviceTypeId
            Property(x => x.DeviceTypeId)
                .HasColumnOrder(0)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired();

            //DeviceDatasheetId
            Property(x => x.DeviceDatasheetId)
                .HasColumnOrder(1)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired();

            //Id
            Property(x => x.Id)
                .HasColumnOrder(2)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired();

            //DeviceBase
            HasRequired(x => x.DeviceBase)
               .WithRequiredDependent(x => x.DeviceMQ);

            //User
            Property(x => x.User)
                .HasColumnOrder(3)
                .HasMaxLength(12)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute { IsUnique = true }));

            //Password
            Property(x => x.Password)
                .HasColumnOrder(4)
                .HasMaxLength(12)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute { IsUnique = true }));

            //ClientId
            Property(x => x.ClientId)
                .HasColumnOrder(5)
                .HasMaxLength(32)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute { IsUnique = true }));

            //Topic
            Property(x => x.Topic)
                .HasColumnOrder(6)
                .HasMaxLength(32)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute { IsUnique = true }));
        }

        #endregion Constructors
    }
}
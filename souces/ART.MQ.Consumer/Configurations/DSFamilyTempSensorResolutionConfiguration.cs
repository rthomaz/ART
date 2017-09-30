﻿using ART.MQ.Consumer.Entities;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity.Infrastructure.Annotations;
using System.Data.Entity.ModelConfiguration;

namespace ART.MQ.Consumer.Configurations
{
    public class DSFamilyTempSensorResolutionConfiguration : EntityTypeConfiguration<DSFamilyTempSensorResolution>
    {
        public DSFamilyTempSensorResolutionConfiguration()
        {
            //Primary Keys
            HasKey(x => x.Id);

            //Id
            Property(x => x.Id)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None)
                .IsRequired();

            //Name
            Property(x => x.Name)
                .HasMaxLength(255)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute { IsUnique = true }));

            //Bits
            Property(x => x.Bits)
                .IsRequired()
                .HasColumnAnnotation(IndexAnnotation.AnnotationName,
                    new IndexAnnotation(new IndexAttribute { IsUnique = true }));

            //Resolution
            Property(x => x.Resolution)
                .HasPrecision(5,4);

            //ResolutionDecimalPlaces
            Ignore(x => x.ResolutionDecimalPlaces);
            
            //ConversionTime
            Property(x => x.ConversionTime)
                .HasPrecision(5, 2);
            
            //Description
            Property(x => x.Description)
                .HasMaxLength(5000)
                .IsOptional();
        }
    }
}
﻿namespace ART.Seguranca.Repository.Entities
{
    using System;

    using Microsoft.AspNet.Identity.EntityFramework;

    public class ApplicationRole : IdentityRole<Guid, ApplicationUserRole>
    {
    }
}
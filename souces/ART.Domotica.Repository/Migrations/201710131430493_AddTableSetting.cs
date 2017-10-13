namespace ART.Domotica.Repository.Migrations
{
    using System.Data.Entity.Migrations;

    public partial class AddTableSetting : DbMigration
    {
        #region Methods

        public override void Down()
        {
            DropTable("dbo.Setting");
        }

        public override void Up()
        {
            CreateTable(
                "dbo.Setting",
                c => new
                    {
                        Id = c.Short(nullable: false),
                        Value = c.String(nullable: false),
                    })
                .PrimaryKey(t => t.Id);
        }

        #endregion Methods
    }
}
import { migrate } from "drizzle-orm/postgres-js/migrator";
import { drizzle } from "drizzle-orm/postgres-js";
import postgres from "postgres";
import * as path from "path";
import * as dotenv from "dotenv";

dotenv.config({ path: path.resolve(process.cwd(), ".env.local") });
dotenv.config({ path: path.resolve(process.cwd(), ".env") });

const connectionString =
  process.env.DATABASE_URL ||
  "postgresql://postgres:postgres@localhost:5432/asthmaphobia";
console.log("Using database:", connectionString.replace(/:[^:]*@/, ":****@")); // Log connection string with password redacted

// Connection for migrations
const migrationClient = postgres(connectionString, { max: 1 });
const db = drizzle(migrationClient);

// Run migrations
async function main() {
  console.log("Running PostgreSQL migrations...");

  await migrate(db, {
    migrationsFolder: path.resolve("./db/migrations"),
  });

  console.log("Migrations complete!");
  await migrationClient.end();
  process.exit(0);
}

main().catch((error) => {
  console.error("Migration failed!", error);
  process.exit(1);
});

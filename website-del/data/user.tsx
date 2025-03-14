import { db } from "@/db";
import { users } from "@/db/schema";
import { eq } from "drizzle-orm";
import { verifySession } from "./auth";
import { cache } from "react";

export const getCurrentUser = cache(async () => {
  const session = await verifySession();
  if (!session) {
    return null;
  }

  const data = await db.query.users.findMany({
    where: eq(users.id, session.userId),
    columns: {
      id: true,
      username: true,
      email: true,
      role: true,
    },
  });

  if (!data.length) return null;

  const user = data[0];

  return user;
});

import { decrypt } from "@/app/lib/session";
import { cookies } from "next/headers";
import { cache } from "react";

export const verifySession = cache(async () => {
  const cookie = (await cookies()).get("session")?.value;
  return await decrypt(cookie);
});

"use server";

import { db } from "@/db";
import { UpdateUserSchema, UpdateUserState } from "../lib/definitions";
import { eq } from "drizzle-orm";
import { hash } from "bcrypt";
import { users } from "@/db/schema";
import { verifySession } from "@/data/auth";

const SALT_ROUNDS = 10;

export async function updateUserProfile(
  state: UpdateUserState,
  formData: FormData
) {
  const session = await verifySession();
  if (!session) {
    return { message: "User not authenticated" };
  }

  const validatedFields = UpdateUserSchema.safeParse({
    username: formData.get("username"),
    email: formData.get("email"),
    password: formData.get("password"),
    confirmPassword: formData.get("confirmPassword"),
  });

  if (!validatedFields.success) {
    return {
      errors: validatedFields.error.flatten().fieldErrors,
    };
  }

  const { username, email, password } = validatedFields.data;

  const updateData: Partial<typeof users.$inferInsert> = {};
  const userId = session.userId;

  if (!userId) {
    return { message: "User not authenticated" };
  }

  if (email) {
    const existingUserByEmail = await db.query.users.findFirst({
      where: (users) => eq(users.email, email),
    });
    if (existingUserByEmail && existingUserByEmail.id !== userId) {
      return { message: "Email is already in use" };
    }

    updateData.email = email;
  }

  if (username) {
    const existingUserByUsername = await db.query.users.findFirst({
      where: (users) => eq(users.username, username),
    });
    if (existingUserByUsername && existingUserByUsername.id !== userId) {
      return { message: "Username is already taken" };
    }

    updateData.username = username;
  }

  if (password) {
    const hashedPassword = await hash(password, SALT_ROUNDS);
    updateData.passwordHash = hashedPassword;
  }

  if (Object.keys(updateData).length === 0) {
    return { message: "No changes to apply" };
  }

  const data = await db
    .update(users)
    .set(updateData)
    .where(eq(users.id, userId))
    .returning();
  const user = data[0];

  if (!user) {
    return { message: "An error occurred while updating your account." };
  }

  return { message: "Account updated successfully." };
}

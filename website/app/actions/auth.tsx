"use server";

import { db } from "@/db";
import { NewUser, users } from "@/db/schema";
import { createSession, deleteSession } from "@/app/lib/session";
import { hash, compare } from "bcrypt";
import { eq } from "drizzle-orm";
import { redirect } from "next/navigation";
import {
  SignupFormState,
  SignupFormSchema,
  SigninFormState,
  SigninFormSchema,
} from "../lib/definitions";

const SALT_ROUNDS = 10;

export async function register(state: SignupFormState, formData: FormData) {
  const validatedFields = SignupFormSchema.safeParse({
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

  const { email, username, password } = validatedFields.data;

  const existingUserByEmail = await db.query.users.findFirst({
    where: (users) => eq(users.email, email),
  });
  if (existingUserByEmail) {
    return { message: "Email is already in use" };
  }

  const existingUserByUsername = await db.query.users.findFirst({
    where: (users) => eq(users.username, username),
  });
  if (existingUserByUsername) {
    return { message: "Username is already taken" };
  }

  const hashedPassword = await hash(password, SALT_ROUNDS);

  const newUser: NewUser = {
    email,
    username,
    passwordHash: hashedPassword,
  };

  const data = await db.insert(users).values(newUser).returning();
  const user = data[0];

  if (!user) {
    return { message: "An error occurred while creating your account." };
  }

  await createSession(user.id);
  redirect("/dashboard");
}

export async function login(state: SigninFormState, formData: FormData) {
  const validatedFields = SigninFormSchema.safeParse({
    email: formData.get("email"),
    password: formData.get("password"),
  });

  if (!validatedFields.success) {
    return {
      errors: validatedFields.error.flatten().fieldErrors,
    };
  }

  const { email, password } = validatedFields.data;

  const user = await db.query.users.findFirst({
    where: (users) => eq(users.email, email),
  });
  if (!user) {
    return { message: "Invalid email or password" };
  }

  const passwordMatch = await compare(password, user.passwordHash);
  if (!passwordMatch) {
    return { message: "Invalid email or password" };
  }

  await createSession(user.id);
  redirect("/dashboard");
}

export async function logout() {
  deleteSession();
  redirect("/login");
}

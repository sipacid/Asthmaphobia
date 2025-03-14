import { JWTPayload } from "jose";
import { z } from "zod";

export const SignupFormSchema = z
  .object({
    username: z
      .string()
      .min(3, { message: "Username must be at least 3 characters long." })
      .max(15, { message: "Username must be at most 15 characters long." })
      .trim(),
    email: z.string().email({ message: "Please enter a valid email." }).trim(),
    password: z
      .string()
      .min(8, { message: "Be at least 8 characters long" })
      .regex(/[a-zA-Z]/, { message: "Contain at least one letter." })
      .regex(/[0-9]/, { message: "Contain at least one number." })
      .regex(/[^a-zA-Z0-9]/, {
        message: "Contain at least one special character.",
      })
      .trim(),
    confirmPassword: z.string().trim(),
  })
  .refine((data) => data.password === data.confirmPassword, {
    message: "Passwords don't match",
    path: ["confirmPassword"],
  });

export type SignupFormState =
  | {
      errors?: {
        name?: string[];
        email?: string[];
        password?: string[];
        confirmPassword?: string[];
      };
      message?: string;
    }
  | undefined;

export const SigninFormSchema = z.object({
  email: z.string().email({ message: "Please enter a valid email." }).trim(),
  password: z.string().trim(),
});

export type SigninFormState =
  | {
      errors?: {
        email?: string[];
        password?: string[];
      };
      message?: string;
    }
  | undefined;

export interface SessionPayload extends JWTPayload {
  userId: string;
  role: "user" | "administrator";
}

export const UpdateUserSchema = z
  .object({
    id: z.string(),
    username: z
      .string()
      .min(3, { message: "Username must be at least 3 characters long." })
      .max(15, { message: "Username must be at most 15 characters long." })
      .trim()
      .optional(),
    email: z
      .string()
      .email({ message: "Please enter a valid email." })
      .trim()
      .optional(),
    password: z
      .string()
      .min(8, { message: "Be at least 8 characters long" })
      .regex(/[a-zA-Z]/, { message: "Contain at least one letter." })
      .regex(/[0-9]/, { message: "Contain at least one number." })
      .regex(/[^a-zA-Z0-9]/, {
        message: "Contain at least one special character.",
      })
      .trim()
      .optional(),
    confirmPassword: z.string().trim().optional(),
  })
  .refine((data) => data.password === data.confirmPassword, {
    message: "Passwords don't match",
    path: ["confirmPassword"],
  });

export type UpdateUserState =
  | {
      error?: {
        username: string;
        email: string;
        password?: string;
        confirmPassword?: string;
      };
      message?: string;
    }
  | undefined;

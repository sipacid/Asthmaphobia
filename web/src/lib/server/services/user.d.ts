import type { User } from '$lib/server/db/schema';

export declare class UserError extends Error {
	code: 'VALIDATION' | 'CONFLICT' | 'NOT_FOUND' | 'UNAUTHORIZED';
	constructor(message: string, code: UserError['code']);
}

export interface UserCreateInput {
	email: string;
	username: string;
	password: string;
	role?: 'user' | 'administrator';
}

export interface UserUpdateInput {
	id: string;
	email?: string;
	username?: string;
	role?: 'user' | 'administrator';
}

export declare class UserService {
	createUser(input: UserCreateInput): Promise<string>;
	getUsers(): Promise<User[]>;
	getUserByID(id: string): Promise<User>;
	getUserByEmail(email: string): Promise<User | null>;
	updateUser(input: UserUpdateInput): Promise<void>;
	deleteUser(id: string): Promise<void>;
	changePassword(id: string, currentPassword: string, newPassword: string): Promise<void>;
	isUsernameAlreadyInUse(username: string): Promise<boolean>;
	isEmailAlreadyInUse(email: string): Promise<boolean>;
	isPasswordValid(password: string, passwordHash: string): Promise<boolean>;
	validateEmail(email: unknown): asserts email is string;
	validateUsername(username: unknown): asserts username is string;
	validatePassword(password: unknown): asserts password is string;
}

export declare const userService: UserService;

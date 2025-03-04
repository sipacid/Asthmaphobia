import { db } from '$lib/server/db';
import { hash, verify } from '@node-rs/argon2';
import * as table from '$lib/server/db/schema';
import { eq } from 'drizzle-orm';

export class UserError extends Error {
	constructor(
		message: string,
		public code: 'VALIDATION' | 'CONFLICT' | 'NOT_FOUND' | 'UNAUTHORIZED'
	) {
		super(message);
		this.name = 'UserError';
	}
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

export class UserService {
	async createUser(input: UserCreateInput): Promise<string> {
		this.validateEmail(input.email);
		this.validateUsername(input.username);
		this.validatePassword(input.password);

		// Check for existing users with same email or username
		if (await this.isEmailAlreadyInUse(input.email)) {
			throw new UserError('Email already in use', 'CONFLICT');
		}

		if (await this.isUsernameAlreadyInUse(input.username)) {
			throw new UserError('Username already in use', 'CONFLICT');
		}

		const id = this.generateUserId();
		const passwordHash = await this.hashPassword(input.password);

		await db.insert(table.user).values({
			id,
			role: input.role || 'user',
			email: input.email.toLowerCase().trim(),
			username: input.username.toLowerCase().trim(),
			passwordHash
		});

		return id;
	}

	async getUsers(): Promise<Omit<table.User, 'passwordHash'>[]> {
		return await db.query.user.findMany({
			columns: {
				id: true,
				email: true,
				username: true,
				role: true,
				createdAt: true,
				updatedAt: true
			}
		});
	}

	async getUserByID(id: string): Promise<table.User> {
		const user = await db.query.user.findFirst({
			where: (users, { eq }) => eq(users.id, id),
			columns: {
				id: true,
				email: true,
				username: true,
				role: true,
				createdAt: true,
				updatedAt: true
			}
		});

		if (!user) {
			throw new UserError(`User with id ${id} not found`, 'NOT_FOUND');
		}

		return user;
	}

	async getUserByEmail(email: string): Promise<table.User | null> {
		if (!email) return null;

		return (
			(await db.query.user.findFirst({
				where: (users, { eq }) => eq(users.email, email.toLowerCase().trim())
			})) || null
		);
	}

	async updateUser(input: UserUpdateInput): Promise<void> {
		const user = await this.getUserByID(input.id);
		if (!user) {
			throw new UserError(`User with id ${input.id} not found`, 'NOT_FOUND');
		}

		const updateData: UserUpdateInput = { id: input.id };

		if (input.email !== undefined) {
			this.validateEmail(input.email);
			if (input.email !== user.email && (await this.isEmailAlreadyInUse(input.email))) {
				throw new UserError('Email already in use', 'CONFLICT');
			}
			updateData.email = input.email.toLowerCase().trim();
		}

		if (input.username !== undefined) {
			this.validateUsername(input.username);
			if (input.username !== user.username && (await this.isUsernameAlreadyInUse(input.username))) {
				throw new UserError('Username already in use', 'CONFLICT');
			}
			updateData.username = input.username.toLowerCase().trim();
		}

		if (input.role !== undefined) {
			updateData.role = input.role;
		}

		await db.update(table.user).set(updateData).where(eq(table.user.id, input.id));
	}

	async deleteUser(id: string): Promise<void> {
		const user = await this.getUserByID(id);
		if (!user) {
			throw new UserError(`User with id ${id} not found`, 'NOT_FOUND');
		}

		await db.delete(table.user).where(eq(table.user.id, id));
	}

	async changePassword(id: string, currentPassword: string, newPassword: string): Promise<void> {
		const user = await this.getUserByID(id);

		// Verify current password
		if (!(await this.isPasswordValid(currentPassword, user.passwordHash))) {
			throw new UserError('Current password is incorrect', 'UNAUTHORIZED');
		}

		// Validate new password
		this.validatePassword(newPassword);

		// Hash and update
		const passwordHash = await this.hashPassword(newPassword);

		await db.update(table.user).set({ passwordHash }).where(eq(table.user.id, id));
	}

	async isUsernameAlreadyInUse(username: string): Promise<boolean> {
		return !!(await db.query.user.findFirst({
			where: (users, { eq }) => eq(users.username, username.toLowerCase().trim())
		}));
	}

	async isEmailAlreadyInUse(email: string): Promise<boolean> {
		return !!(await db.query.user.findFirst({
			where: (users, { eq }) => eq(users.email, email.toLowerCase().trim())
		}));
	}

	async isPasswordValid(password: string, passwordHash: string): Promise<boolean> {
		return await verify(passwordHash, password, {
			memoryCost: 19456,
			timeCost: 2,
			outputLen: 32,
			parallelism: 1
		});
	}

	validateEmail(email: unknown): asserts email is string {
		if (
			typeof email !== 'string' ||
			!email.includes('@') ||
			email.length < 3 ||
			email.length > 255
		) {
			throw new UserError('Invalid email address', 'VALIDATION');
		}
	}

	validateUsername(username: unknown): asserts username is string {
		if (
			typeof username !== 'string' ||
			username.length < 3 ||
			username.length > 31 ||
			!/^[a-z0-9_-]+$/.test(username.toLowerCase())
		) {
			throw new UserError(
				'Username must be 3-31 characters and contain only letters, numbers, underscores, and hyphens',
				'VALIDATION'
			);
		}
	}

	validatePassword(password: unknown): asserts password is string {
		if (typeof password !== 'string' || password.length < 6 || password.length > 255) {
			throw new UserError('Password must be at least 6 characters', 'VALIDATION');
		}
	}

	private generateUserId(): string {
		return Math.random().toString(36).slice(2);
	}

	private async hashPassword(password: string): Promise<string> {
		return await hash(password, {
			memoryCost: 19456,
			timeCost: 2,
			outputLen: 32,
			parallelism: 1
		});
	}
}

// Create a singleton instance
export const userService = new UserService();

import { sql } from 'drizzle-orm';
import { pgEnum, pgTable, text, timestamp, boolean, uuid, integer } from 'drizzle-orm/pg-core';

export const roleEnum = pgEnum('role', ['user', 'administrator']);

export const user = pgTable('user', {
	id: text('id').primaryKey(),
	role: roleEnum('role').notNull().default('user'),
	email: text('email').notNull().unique(),
	username: text('username').notNull().unique(),
	passwordHash: text('password_hash').notNull(),
	createdAt: timestamp('created_at', { withTimezone: true, mode: 'date' }).defaultNow(),
	updatedAt: timestamp('updated_at', { withTimezone: true, mode: 'date' }).defaultNow()
});

export const userLogin = pgTable('user_login', {
	id: uuid('id').primaryKey().defaultRandom(),
	userId: text('user_id')
		.notNull()
		.references(() => user.id),
	ipAddress: text('ip_address').notNull(),
	userAgent: text('user_agent').notNull(),
	createdAt: timestamp('created_at', { withTimezone: true, mode: 'date' }).defaultNow()
});

export const session = pgTable('session', {
	id: text('id').primaryKey(),
	userId: text('user_id')
		.notNull()
		.references(() => user.id),
	expiresAt: timestamp('expires_at', { withTimezone: true, mode: 'date' }).notNull()
});

export const postTypeEnum = pgEnum('post_type', ['news', 'release']);

export const posts = pgTable('posts', {
	id: uuid('id').primaryKey().defaultRandom(),
	title: text('title').notNull(),
	content: text('content').notNull(),
	type: postTypeEnum('type').notNull(),
	authorId: text('author_id')
		.notNull()
		.references(() => user.id),
	published: boolean('published').notNull().default(false),
	version: text('version'),
	createdAt: timestamp('created_at', { withTimezone: true, mode: 'date' }).defaultNow(),
	updatedAt: timestamp('updated_at', { withTimezone: true, mode: 'date' }).defaultNow()
});

export const downloadTypeEnum = pgEnum('download_type', ['loader', 'library']);

export const downloads = pgTable('downloads', {
	id: uuid('id').primaryKey().defaultRandom(),
	userId: text('user_id').references(() => user.id),
	type: downloadTypeEnum('type').notNull(),
	ipAddress: text('ip_address').notNull(),
	createdAt: timestamp('created_at', { withTimezone: true, mode: 'date' }).defaultNow()
});

export const faq = pgTable('faq', {
	id: uuid('id').primaryKey().defaultRandom(),
	question: text('question').notNull(),
	answer: text('answer').notNull(),
	ranking: integer('ranking').notNull().default(0),
	createdAt: timestamp('created_at', { withTimezone: true, mode: 'date' }).defaultNow(),
	updatedAt: timestamp('updated_at', { withTimezone: true, mode: 'date' }).defaultNow()
});

export type Session = typeof session.$inferSelect;
export type User = typeof user.$inferSelect;
export type UserLogin = typeof userLogin.$inferSelect;
export type Post = typeof posts.$inferSelect;
export type Download = typeof downloads.$inferSelect;
export type FAQ = typeof faq.$inferSelect;

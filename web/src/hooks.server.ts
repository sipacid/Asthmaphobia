import type { Handle } from '@sveltejs/kit';
import * as auth from '$lib/server/auth.js';

const handleAuth: Handle = async ({ event, resolve }) => {
	console.log('Request headers:', event.request.headers);

	const sessionToken = event.cookies.get(auth.sessionCookieName);
	if (!sessionToken) {
		event.locals.user = null;
		event.locals.session = null;
		return resolve(event);
	}

	const { session, user } = await auth.validateSessionToken(sessionToken);
	if (session) {
		auth.setSessionTokenCookie(event, sessionToken, session.expiresAt);
	} else {
		auth.deleteSessionTokenCookie(event);
	}

	event.locals.user = user;
	event.locals.session = session;

	const response = await resolve(event);

	// Security headers that also positively impact SEO rankings
	response.headers.set('X-Content-Type-Options', 'nosniff');
	response.headers.set('X-Frame-Options', 'SAMEORIGIN');
	response.headers.set('Referrer-Policy', 'strict-origin-when-cross-origin');
	response.headers.set('Permissions-Policy', 'camera=(), microphone=(), geolocation=()');

	// Set caching headers for static assets
	if (event.url.pathname.startsWith('/images/')) {
		response.headers.set('Cache-Control', 'public, max-age=604800, immutable');
	}

	return response;
};

export const handle: Handle = handleAuth;

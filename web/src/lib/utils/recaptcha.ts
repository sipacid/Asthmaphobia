import { env as envPublic } from '$env/dynamic/public';

declare global {
	interface Window {
		grecaptcha: {
			enterprise: {
				execute: (siteKey: string, options: { action: string }) => Promise<string>;
				ready: (callback: () => void) => void;
			};
		};
	}
}

/**
 * Get a reCAPTCHA token for the specified action
 *
 * @param action The action name for the token (e.g., 'login', 'register')
 * @returns A promise that resolves to the reCAPTCHA token
 */
export async function getReCaptchaToken(action: string): Promise<string> {
	try {
		return new Promise((resolve) => {
			window.grecaptcha.enterprise.ready(async () => {
				try {
					const token = await window.grecaptcha.enterprise.execute(
						envPublic.PUBLIC_RECAPTCHA_SITE_KEY!,
						{
							action
						}
					);
					resolve(token);
				} catch (err) {
					console.error('Error executing reCAPTCHA:', err);
					resolve('');
				}
			});
		});
	} catch (error) {
		console.error('Error getting reCAPTCHA token:', error);
		return '';
	}
}

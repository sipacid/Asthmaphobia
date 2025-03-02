import { GOOGLE_API_KEY, GOOGLE_PROJECT_ID, RECAPTCHA_SITE_KEY } from '$env/static/private';

/**
 * Verify a reCAPTCHA token with Google's API
 *
 * @param token The reCAPTCHA token from the client
 * @param expectedAction The expected action name (e.g., 'login', 'register')
 * @param minimumScore The minimum score to consider as valid (0.0 to 1.0, default is 0.5)
 * @returns An object with verification result and error message if applicable
 */
export async function verifyRecaptchaToken(
	token: string,
	expectedAction: string,
	userAgent: string,
	userIpAddress: string,
	minimumScore = 0.5
): Promise<{ success: boolean; message?: string }> {
	try {
		if (!token) {
			return {
				success: false,
				message: 'reCAPTCHA verification failed: No token provided'
			};
		}

		// TODO: Implement ja3 fingerprinting
		const response = await fetch(
			`https://recaptchaenterprise.googleapis.com/v1/projects/${GOOGLE_PROJECT_ID}/assessments?key=${GOOGLE_API_KEY}`,
			{
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					event: {
						token,
						siteKey: RECAPTCHA_SITE_KEY,
						userAgent,
						userIpAddress,
						expectedAction
					}
				})
			}
		);
		const data = await response.json();

		if (!response.ok) {
			return {
				success: false,
				message: 'reCAPTCHA verification failed: Unknown error'
			};
		}

		if (data.tokenProperties.valid !== true) {
			return {
				success: false,
				message: 'reCAPTCHA verification failed: Invalid token'
			};
		}

		if (expectedAction !== data.event.expectedAction) {
			console.error(
				'reCAPTCHA verification failed due to action mismatch. Expected:',
				expectedAction,
				'Actual:',
				data.event.expectedAction
			);
			return {
				success: false,
				message: 'reCAPTCHA verification failed: Invalid action'
			};
		}

		if (data.riskAnalysis.score < minimumScore) {
			return {
				success: false,
				message: `Suspicious activity detected. Please try again.`
			};
		}

		return { success: true };
	} catch (error) {
		console.error('Error verifying reCAPTCHA token:', error);
		return {
			success: false,
			message: 'reCAPTCHA verification failed: Server error'
		};
	}
}

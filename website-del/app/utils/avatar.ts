type AvatarColors = {
  background: string;
  text: string;
};

/**
 * Generates a consistent color based on a user id
 * @param userId string user identifier
 * @returns object with background and text colors
 */
export function getAvatarColors(userId: string): AvatarColors {
  // Define color palettes that match our purple theme
  const backgroundColors = [
    "bg-purple-600",
    "bg-indigo-600",
    "bg-blue-600",
    "bg-violet-600",
    "bg-fuchsia-600",
    "bg-pink-600",
  ];

  // Hash the user id to get a consistent color
  let hash = 0;
  for (let i = 0; i < userId.length; i++) {
    hash = userId.charCodeAt(i) + ((hash << 5) - hash);
  }

  const backgroundIndex = Math.abs(hash) % backgroundColors.length;

  return {
    background: backgroundColors[backgroundIndex],
    text: "text-white",
  };
}

/**
 * Generates a data URL for a profile picture with a letter
 * @param username string username
 * @param userId string unique user identifier
 * @returns string data URL of SVG image
 */
export function generateLetterAvatar(username: string, userId: string): string {
  // Get the first letter of the username
  const letter = username.charAt(0).toLowerCase();

  // Get colors based on userId for consistency
  const colors = getAvatarColors(userId);
  const bgColor = colors.background.replace("bg-", "");

  // Map Tailwind colors to their hex values
  const colorMap: Record<string, string> = {
    "purple-600": "#9333ea",
    "indigo-600": "#4f46e5",
    "blue-600": "#2563eb",
    "violet-600": "#7c3aed",
    "fuchsia-600": "#c026d3",
    "pink-600": "#db2777",
  };

  // Get the hex color
  const bgHex = colorMap[bgColor] || "#9333ea"; // Default to purple if not found

  // Create SVG with circular background and centered letter
  const svg = `
    <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 100">
      <circle cx="50" cy="50" r="50" fill="${bgHex}" />
      <text 
        x="50" 
        y="50" 
        font-family="Arial, sans-serif" 
        font-size="40" 
        font-weight="bold"
        fill="white" 
        text-anchor="middle" 
        dominant-baseline="central"
      >
        ${letter}
      </text>
    </svg>
  `;

  // Convert SVG to a data URL
  return `data:image/svg+xml;base64,${btoa(svg)}`;
}

/**
 * Gets an avatar image URL for a user
 * @param username string username
 * @param userId string user identifier
 * @param customAvatar string|undefined custom avatar URL
 * @returns string URL to avatar image
 */
export function getUserAvatar(
  username: string,
  userId: string,
  customAvatar?: string
): string {
  // If the user has a custom avatar, use it
  if (customAvatar && !customAvatar.includes("default-avatar")) {
    return customAvatar;
  }

  // Otherwise generate a letter-based avatar
  return generateLetterAvatar(username, userId || username);
}

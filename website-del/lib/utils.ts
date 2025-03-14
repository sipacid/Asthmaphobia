/**
 * Format a date to display in a human-friendly way
 * Example: "15 Apr 2023"
 */
export function formatDate(date: Date): string {
  return date
    .toLocaleDateString("en-US", {
      day: "numeric",
      month: "short",
      year: "numeric",
    })
    .replace(",", ""); // Remove the comma that appears by default
}

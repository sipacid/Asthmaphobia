import { appInfo } from "../../config/appInfo";
import newsData from "../../data/news.json";

export async function GET() {
  const latestVersionNews = newsData
    .filter((item) => item.category === "update" && item.version)
    .sort((a, b) => new Date(b.date).getTime() - new Date(a.date).getTime())[0];

  return new Response(
    JSON.stringify({
      latest_version: latestVersionNews?.version || appInfo.version,
      release_date:
        latestVersionNews?.date || new Date().toISOString().split("T")[0],
      changelog: latestVersionNews?.content || [],
    }),
    {
      headers: {
        "Content-Type": "application/json",
      },
    },
  );
}

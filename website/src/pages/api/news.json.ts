import newsData from "../../data/news.json";

export async function GET() {
  return new Response(
    JSON.stringify({
      items: newsData,
    }),
    {
      headers: {
        "Content-Type": "application/json",
      },
    },
  );
}

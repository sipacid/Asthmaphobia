import rss from "@astrojs/rss";
import { getCollection } from "astro:content";

export async function GET(context) {
  const news = await getCollection("news");

  return rss({
    title: "Asthmaphobia's updates",
    description: "News & Update feed of Asthmaphobia",
    site: context.site,
    customData: `<language>en-us</language>`,
    items: news.map((item) => ({
      title: item.data.title,
      pubDate: item.data.date,
      link: `/news#${item.id}`,
    })),
  });
}

import { defineCollection, z } from "astro:content";
import { file } from "astro/loaders";

const news = defineCollection({
  loader: file("src/data/news.json"),
  schema: z.object({
    id: z.number(),
    title: z.string(),
    date: z.coerce.date(),
    category: z.string(),
    version: z.string().optional(),
    content: z.array(z.string()),
  }),
});

export const collections = { news };

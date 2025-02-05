using System.Diagnostics;

public class Dice
{
    private int min;
    private int max;

    private ActivitySource activitySource;

    public Dice(int min, int max,  ActivitySource activitySource)
    {
        this.min = min;
        this.max = max;
        this.activitySource = activitySource;
    }

    public List<int> rollTheDice(int rolls)
    {
        {
            using var activityParentOne = activitySource.StartActivity("parnet-one");
            using var activityParentTwo = activitySource.StartActivity("parnet-two");
            using var activityParentThree = activitySource.StartActivity("parnet-three");
            var links = new List<ActivityLink>
                {
                    new ActivityLink(activityParentOne.Context),
                    new ActivityLink(activityParentTwo.Context),
                    new ActivityLink(activityParentThree.Context)
                };

            using var activity = activitySource.StartActivity(
                ActivityKind.Internal,
                name: "activity-with-links",
                links: links);

        }


        List<int> results = new List<int>();

        // It is recommended to create activities, only when doing operations that are worth measuring independently.
        // Too many activities makes it harder to visualize in tools like Jaeger.
        using (var myActivity = activitySource.StartActivity("rollTheDice"))
        {
            myActivity?.AddEvent(new("Init rolling dice"));

            for (int i = 0; i < rolls; i++)
            {
                results.Add(rollOnce());
            }

            var eventTags = new ActivityTagsCollection
            {
                { "operation", "calculate-pi" },
                { "result", 3.14159 }
            };

            myActivity?.AddEvent(new("End rolling dice", DateTimeOffset.Now, eventTags));

            return results;
        }
    }

    private int rollOnce()
    {
        using var myActivity = activitySource.StartActivity("roll the dice once");
        var result = Random.Shared.Next(min, max + 1);
        myActivity?.SetTag("dicelib.rolled", result);
        return result;
    }
}

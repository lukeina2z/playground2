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
        List<int> results = new List<int>();

        // It is recommended to create activities, only when doing operations that are worth measuring independently.
        // Too many activities makes it harder to visualize in tools like Jaeger.
        using (var myActivity = activitySource.StartActivity("rollTheDice"))
        {
            for (int i = 0; i < rolls; i++)
            {
                results.Add(rollOnce());
            }

            return results;
        }
    }

    private int rollOnce()
    {
        return Random.Shared.Next(min, max + 1);
    }
}

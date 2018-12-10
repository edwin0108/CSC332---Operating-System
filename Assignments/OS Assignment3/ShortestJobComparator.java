import java.util.Comparator;

public class ShortestJobComparator implements Comparator<process>
{
    @Override
    public int compare(process x, process y)
    {
        if(x.est_remain_time == y.est_remain_time)
        {
            return x.arrival_time < y.arrival_time ? -1 : 1; 
        }

        return x.est_remain_time < y.est_remain_time ? -1 : 1;
        
    }
}
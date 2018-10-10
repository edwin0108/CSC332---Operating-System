import java.io.Serializable;
import java.util.Comparator;

public class process implements Serializable, Comparable<process>
{
    public String program_name;
    public int pid;
    public String state;
    public int priority;
    public int interruptable;
    public int est_run_time;
    public int est_remain_time;

    public process(String proc)
    {
        /**split the process information */
        String[] split = proc.split(",");
        program_name = split[0];
        pid = Integer.parseInt(split[1]);
        state = split[2];
        priority = Integer.parseInt(split[3]);
        interruptable = Integer.parseInt(split[4]);
        est_run_time = Integer.parseInt(split[5]);
        est_remain_time = Integer.parseInt(split[6]);
    }

    /**subtracts 200 cycle per each exec*/
    public void cycle_subtract(){
        if (this.est_remain_time > 200)
            this.est_remain_time -= 200;
        else
            this.est_remain_time = 0;
    }

    /** print out the current process information */
    public void printprocess()
    {
        System.out.println("CPU: Exec "
                + program_name + ","
                + pid + ","
                + state + ","
                + priority + ","
                + interruptable + ","
                + est_run_time + ","
                + est_remain_time);
    }

    @Override
    public int compareTo(process o) {
        return this.priority > o.priority ? 1 : (this.priority < o.priority ? -1 : 0);
    }
}

public class process
{
    public int arrival_time;
    public String program_name;
    public int pid;
    public String state;
    public int priority;
    public int interruptable;
    public int est_run_time;
    public int est_remain_time;
    public int waiting_time;
    public int time_quantum;

    public process(String proc)
    {
        /**split the process information */
        String[] split = proc.split(",");
        arrival_time = Integer.parseInt(split[0]);
        program_name = split[1];
        pid = Integer.parseInt(split[2]);
        state = split[3];
        priority = Integer.parseInt(split[4]);
        interruptable = Integer.parseInt(split[5]);
        est_run_time = Integer.parseInt(split[6]);
        est_remain_time = Integer.parseInt(split[7]);
        waiting_time = 0;
    }
}

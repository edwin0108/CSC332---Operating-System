import java.io.*;
import java.util.*;
import java.io.IOException;


public class CPU_Emulator {

    //NOTE: TURNAROUND TIME IS NOT YET IMPLEMENTED
    public static void main(String[] args) throws IOException
    {
        Queue<process> scheduledTask = readfile();
        Queue<process> schedulerQueue = null;
        int scheduling_case = Integer.parseInt(args[0]);
        if (scheduling_case == 1) {
            schedulerQueue = new LinkedList<>();
            System.out.println("-----FIFO Scheduling-----");
            noPreEmptionScheduling(scheduledTask, schedulerQueue);
        }
        else if (scheduling_case == 2) {
            schedulerQueue = new PriorityQueue<process>(20, new ShortestJobComparator());
            System.out.println("-----Shortest Job Scheduling-----");
            noPreEmptionScheduling(scheduledTask, schedulerQueue);
        }
        else if (scheduling_case == 3) {
            schedulerQueue = new PriorityQueue<process>(20, new PriorityComparator());
            System.out.println("-----Priority Scheduling-----");
            noPreEmptionScheduling(scheduledTask, schedulerQueue);
        }
        else if (scheduling_case == 4) {
            schedulerQueue = new LinkedList<>();
            System.out.println("-----Round Robin FIFO: 10 units-----");
            noPreEmptionTimeQuantumScheduling(scheduledTask, schedulerQueue, 10);
        }
        else if (scheduling_case == 5) {
            schedulerQueue = new LinkedList<>();
            System.out.println("-----Round Robin FIFO: 100 units-----");
            noPreEmptionTimeQuantumScheduling(scheduledTask, schedulerQueue, 100);
        }
        else if (scheduling_case == 6) {
            schedulerQueue = new LinkedList<>();
            System.out.println("-----Round Robin FIFO: 1000 units-----");
            noPreEmptionTimeQuantumScheduling(scheduledTask, schedulerQueue, 1000);
        }
        else if (scheduling_case == 7) {
            schedulerQueue = new PriorityQueue<process>(20, new ShortestJobComparator());
            System.out.println("-----Round Robin Shortest Job-----");
            noPreEmptionTimeQuantumScheduling(scheduledTask, schedulerQueue, 50);
        }
        else {
            schedulerQueue = new PriorityQueue<process>(20, new PriorityComparator());
            System.out.println("-----Round Robin Priority-----");
            noPreEmptionTimeQuantumScheduling(scheduledTask, schedulerQueue, 50);
        }
    }

    //read process file line by line and load into scheduler_queue
    public static Queue<process> readfile(){
        Queue<process> schedule_task = new LinkedList<>();
        try(BufferedReader br = new BufferedReader(new FileReader("processes_3.txt"))){
            String line = "";
            while ((line = br.readLine()) != null)
            {
                schedule_task.add(new process(line));
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
        return schedule_task;
    }

    public static void noPreEmptionScheduling(Queue<process> scheduledTask, Queue<process> SchedulingQueue){
        //keep track of the current time
        int timer = 0; 

        // state of CPU -  true: running; false: ready
        boolean flag = false; 
        int context_switch = 0;

        //for analysis purposes
        ArrayList<process> completedProcess = new ArrayList<process>();

        process CPUProcess = null;
        process currentProcess = scheduledTask.remove();
        
        while(scheduledTask.peek() != null || SchedulingQueue.peek() != null || flag == true){
            if(timer == currentProcess.arrival_time){
                //send the currentTask to scheduleQueue
                System.out.println("Scheduler: " + currentProcess.program_name + " entered the schedulingQueue at: "
                        + timer);
                SchedulingQueue.add(currentProcess);
                if(scheduledTask.peek() != null){
                    currentProcess = scheduledTask.remove();
                }

                //first process is passing to the scheduling queue
                if(flag == false && SchedulingQueue.peek() != null){
                    CPUProcess = SchedulingQueue.remove();
                    flag = true;
                }
            }

            if(flag == true){
                if(CPUProcess.est_remain_time != 0){
                    CPUProcess.est_remain_time --;
                    if(SchedulingQueue.peek() != null){
                        for(process pendingProcess : SchedulingQueue){
                            pendingProcess.waiting_time ++;
                        }
                    }
                }

                else{
                    completedProcess.add(CPUProcess);
                    System.out.println("CPUEmulator: " + CPUProcess.program_name + " is finished at time " + timer);
                    if(SchedulingQueue.peek() != null){
                        timer += 2;
                        for(process pendingProcess : SchedulingQueue){
                            pendingProcess.waiting_time += 2;
                        }
                        CPUProcess = SchedulingQueue.remove();
                        CPUProcess.est_remain_time --;
                    }
                    else{
                        flag = false;
                        int sum_wait_time = 0;
                        int longest_wait_time = 0;
                        for (process finished_process : completedProcess) {
                            sum_wait_time += finished_process.waiting_time;
                            if (longest_wait_time < finished_process.waiting_time) {
                                longest_wait_time = finished_process.waiting_time;
                            }
                        }
                        System.out.println("Total time used: " + timer);
                        System.out.println("Longest wait time: " + longest_wait_time);
                        System.out.println("Average wait time: " + sum_wait_time / 14.0);
                        System.out.println(
                                "-----------------------------------------------------------");
                        try(FileWriter fw = new FileWriter("myfile.txt", true);
                            BufferedWriter bw = new BufferedWriter(fw);
                            PrintWriter out = new PrintWriter(bw))
                                {
                                    out.print((sum_wait_time/14) + ",");
                                }
                                catch(IOException e){
                                    e.printStackTrace();
                                }
                    }
                }
            }
            timer ++;
        }
    }

    public static void noPreEmptionTimeQuantumScheduling(Queue<process> scheduledTask, Queue<process> SchedulingQueue, int timeQuantum){
        //keep track of the current time
        int timer = 0; 

        int context_switch = 0;
        // state of CPU -  true: running; false: ready
        boolean flag = false; 

        //for analysis purposes
        ArrayList<process> completedProcess = new ArrayList<process>();

        int fixedTime = timeQuantum;

        process CPUProcess = null;
        process currentProcess = scheduledTask.remove();
        
        while(scheduledTask.peek() != null || SchedulingQueue.peek() != null || flag == true){
            if(timer == currentProcess.arrival_time){
                //send the currentTask to scheduleQueue
                System.out.println("Scheduler: " + currentProcess.program_name + " entered the schedulingQueue at: "
                        + timer);
                SchedulingQueue.add(currentProcess);
                if(scheduledTask.peek() != null){
                    currentProcess = scheduledTask.remove();
                }

                //first process is passing to the scheduling queue
                if(flag == false && SchedulingQueue.peek() != null){
                    CPUProcess = SchedulingQueue.remove();
                    flag = true;
                }
            }

            if(flag == true){
                if(CPUProcess.est_remain_time != 0){
                    if(fixedTime != 0){
                        CPUProcess.est_remain_time --;
                        fixedTime --;
                        if(SchedulingQueue.peek() != null){
                            for(process pendingProcess : SchedulingQueue){
                                pendingProcess.waiting_time ++;
                            }
                        }
                    }
                    else {
                        process next_process = null;
                        System.out.println("Cpu Emulator: End of time quantum. " + CPUProcess.program_name
                                + " at time " + timer + ". Estimate Remaining Time: " + CPUProcess.est_remain_time);
                        context_switch ++; // context switch to next process
                        timer ++; // add 1 units context switch
                        // check if any new process comes
                        if (timer == currentProcess.arrival_time) {
                            next_process = CPUProcess;
                            next_process.waiting_time += 1;
                            System.out.println("Scheduler: " + next_process.program_name
                                    + " is entered the scheduling Queue at time " + timer);
                            if (scheduledTask.peek() != null) {
                                currentProcess = scheduledTask.remove();
                            }
                        }
                        // add one unit of wait time an turnaround time in ready scheduler
                        if (SchedulingQueue.peek() != null) {

                            for(process pendingProcess : SchedulingQueue){
                                pendingProcess.waiting_time ++;
                            }
                        }
                        // one process arrives during context switch
                        if (next_process != null) {
                            SchedulingQueue.add(next_process);
                            next_process = null;
                        }
                        timer += 1; // add 1 units context switch
                        // check if any new process comes
                        if (timer == currentProcess.arrival_time) {
                            next_process = CPUProcess;
                            next_process.waiting_time += 1;
                            System.out.println("Scheduler: " + next_process.program_name
                                    + " is entered the scheduling Queue at time " + timer);
                            if (scheduledTask.peek() != null) {
                                CPUProcess = scheduledTask.remove();
                            }
                        }
                        // add one unit of wait time an turnaround time in ready scheduler
                        if (SchedulingQueue.peek() != null) {

                            for (process pendingProcess : SchedulingQueue) {
                                pendingProcess.waiting_time ++; // 1 unit wait time for process in scheduler
                                //pendingProcess.turnaroundTime ++; // 1 unit turnaround_time for process in scheduler
                            }
                        }
                        // one process arrives during context switch
                        if (next_process != null) {
                            SchedulingQueue.add(next_process);
                            next_process = null;
                        }

                        CPUProcess.waiting_time += 2;
                        if (SchedulingQueue.peek() != null) {

                            process temp = CPUProcess;
                            CPUProcess = SchedulingQueue.remove(); // load the next process to cpu
                            SchedulingQueue.add(temp);
                        }
                        fixedTime = timeQuantum;
                        System.out.println("Cpu Emulator: Ready to process " + CPUProcess.program_name + " at time "
                                + timer + ". Estimate Remaining Time: " + CPUProcess.est_remain_time);
                        CPUProcess.est_remain_time -= 1; // decrement est_remaining time
                        fixedTime -= 1;
                    }
                }

                else{
                    completedProcess.add(CPUProcess);
                    System.out.println("CPUEmulator: " + CPUProcess.program_name + " is finished at time " + timer);
                    if(SchedulingQueue.peek() != null){
                        context_switch ++ ;
                        //adding time 2 times to prevent(check) skipping process's arrivial time when context switch triggered.
                        timer ++ ;
                        if(timer == CPUProcess.arrival_time){
                            SchedulingQueue.add(CPUProcess);
                            System.out.println("Scheduler: " + CPUProcess.program_name
                                    + " is entered the scheduling Queue at time " + timer);
                            if(scheduledTask.peek() != null){
                                CPUProcess = scheduledTask.remove();
                            }
                        }
                        timer ++;
                        if(timer == CPUProcess.arrival_time){
                            SchedulingQueue.add(CPUProcess);
                            System.out.println("Scheduler: " + CPUProcess.program_name
                                    + " is entered the scheduling Queue at time " + timer);
                            if(scheduledTask.peek() != null){
                                CPUProcess = scheduledTask.remove();
                            }
                        }
                        for(process pendingProcess : SchedulingQueue){
                            pendingProcess.waiting_time += 2;
                        }
                        CPUProcess = SchedulingQueue.remove();
                        System.out.println("Cpu Emulator: Ready to process " + CPUProcess.program_name + " at time "
                                + timer + ". Estimate Remaining Time: " + CPUProcess.est_remain_time);
                        CPUProcess.est_remain_time --;
                        fixedTime = timeQuantum;
                        fixedTime--;
                    }
                    else{
                        flag = false;
                        int sum_wait_time = 0;
                        int longest_wait_time = 0;
                        for (process finished_process : completedProcess) {
                            sum_wait_time += finished_process.waiting_time;
                            if (longest_wait_time < finished_process.waiting_time) {
                                longest_wait_time = finished_process.waiting_time;
                            }
                        }
                        System.out.println("Total time used: " + timer);
                        System.out.println("Longest wait time: " + longest_wait_time);
                        System.out.println("Average wait time: " + sum_wait_time / 14.0);
                        System.out.println(
                                "-----------------------------------------------------------");
                        try(FileWriter fw = new FileWriter("myfile.txt", true);
                            BufferedWriter bw = new BufferedWriter(fw);
                            PrintWriter out = new PrintWriter(bw))
                        {
                            out.print((sum_wait_time/14) + ",");
                        }
                        catch(IOException e){
                            e.printStackTrace();
                        }
                    }
                }
            }
            timer ++;
        }
    }
}



package com.example.ThymeleafProject;

public class DroneObj {
    private int droneID;
    private String status;
    private String currentTask;

    public DroneObj(int droneID, String status, String currentTask) {
        this.droneID = droneID;
        this.status = status;
        this.currentTask = currentTask;
    }

    public int getDroneID() {
        return this.droneID;
    }

    public void setDroneID(int droneID) {
        this.droneID = droneID;
    }

    public String getStatus() {
        return this.status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getCurrentTask() {
        return this.currentTask;
    }

    public void setCurrentTask(String currentTask) {
        this.currentTask = currentTask;
    }

    @Override
    public String toString() {
        return "DroneObj{droneID=" + this.droneID + ", status='" + this.status + "', currentTask='" + this.currentTask + "'}";
    }
}

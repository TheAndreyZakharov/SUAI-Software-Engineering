package com.example.ThymeleafProject;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import org.springframework.security.core.GrantedAuthority;
import java.security.Principal;

@Controller
@RequestMapping("/drones")
class DroneController {

    private List<DroneObj> drones = new ArrayList<>();

    @GetMapping("")
    public String getAllDrones(Model model) {
        model.addAttribute("drones", drones);
        return "drones";
    }

    @PostMapping("/add")
    public String addDrone(@ModelAttribute DroneObj drone) {
        drones.add(drone);
        return "redirect:/drones";
    }

    @PostMapping("/delete/{id}")
    public String deleteDrone(@PathVariable int id) {
        drones.removeIf(drone -> drone.getDroneID() == id);
        return "redirect:/drones";
    }
}

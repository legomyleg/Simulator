# 6-DOF Simulator

A terminal-based rocket simulator meant to provide noisy sensor data to enable HIL testing with flight hardware.

## Model

The rocket will eventually be modelled as:
$$
x = [\mathbf r, \mathbf v, \mathbf q, \boldsymbol \omega, m],
$$

where 

$$
\mathbf r = [x, y, z], \quad \mathbf v = [v_x, v_y, v_z], \quad \mathbf q = [q_w, q_x, q_y, q_z], \quad \boldsymbol \omega = [\omega_x, \omega_y, \omega_z].
$$

### Position: $\mathbf r$



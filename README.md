# Getting Started

If you want to avoid running the executable in sudo. Run the following.

```
sudo usermod -aG kvm $USER # Adds current user to the kvm group
newgrp kvm                 # Refreshes the group
```

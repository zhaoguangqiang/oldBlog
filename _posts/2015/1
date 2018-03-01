
## 1. Install Jenkins
**preinstallation：Java 8 (either a JRE or Java Development Kit (JDK) is fine)**

### 1) Install jenkins on linux
Linux(Ubuntu) update jenkens source

```
wget -q -O - https://pkg.jenkins.io/debian/jenkins-ci.org.key | sudo apt-key add –
sudo sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'
sudo apt-get update
sudo apt-get install Jenkins
```

### 2) Install jenkins on windows
Download jenkins from https://jenkins.io/ and setup.

## 2. Initialize Jenkins on web

1. Online authentication  
2. Setup plugins
3. config your username/password

## 3. Config Jenkins master(linux) and slave(windows)

1. config master's communication with slave
    ```
    Jenkins->Manage Jenkins->Configure Global Security
        "Agents"
            "TCP port for JNLP agents":"Random"
    
    ```
    
2. config slave on master
    ```
    Jenkins->Manage Jenkins->Manage Nodes
        click "New node"
            config "Node Name"
            select "Permanant Agent"
        click "OK" Enter Detailed Configuration page.

        fill "Remote root directory", root path on slave node.
        fill "Labels":"windows".
        fill "Usage":"Use this node as much as possible".
        fill "Launch method":"Launch agent via Java Web Start",this method be suitable for windows.
        Node Properties
            select "Tool Locations"
                fill "Name":"git"
                fill "Home":"your windows git path"
        click "Save"
    ```
    
3. install slave agent on windows
    ```
    Jenkins->Manage Jenkins->Manage Nodes
        click the slave name you created just now.
        click "launch" to download named "slave-agent.jnlp" agent from this page.
        move this agent to your "Remote root directory".
        run "javaws slave-agent.jnlp" on windows's cmd.
        it will pop a windows, if appear "connected" on it, justify master had been found this agent.
        click "file"->"install a windows" on this windows, it'll start this agent service when computer startup every time.
    ```
    
4. create slave pipeline
    ```
    Jenkins->New item
        "item name":"Your item name"
        select "pipeline" job.
        click "ok".
        You will jump to a pipeline config page.
        
        "Pipeline"
            "Definition":"Pipeline script from SCM"
            "SCM":"git"
            "Repositories"
                "Repository URL":"Your Repository URL"
                "Credentials":"Your Credentials"
            "Script Path":"Jenkinsfile"
        click "save".
        Finish config pipeline.
    ```
        
5. Note
    ```
    Jenkinsfile "agent" parameter must be similar with slave labels.Otherwise slave cannot identify this job.
    ```
    



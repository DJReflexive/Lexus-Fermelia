# wytalk

A tool for exchanging simple text messages between a client and a server.

<br>




## Usage

After having compiled with "make":

```
(server side)
./wytalkD 

OR

(client side)
./wytalkC <Hostname>
```

- Hostname is the hostname of the server side, which can be found by running the "hostname" command
- This requires two terminal windows or two machines that can connect via the same hostname


<br>


## Example Usage


Server side:
```
lexus/wytalk>hostname
my.client.hostname
lexus/wytalk>./wytalkD
Hello! I am the client!
Hi! I am the server!
How are you today?
I am great! Thanks for asking
lexus/wytalk>
```

Client side:
```
lexus/wytalk>./wytalkC my.client.hostname
Hello! I am the client!
Hi! I am the server!
How are you today?
I am great! Thanks for asking
lexus/wytalk>
```


###### Note that this messaging system is turn based. You cannot send two messages in a row from one side. You must send a message and wait for the other side to return a message before you can send another. The client goes first.

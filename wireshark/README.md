# Using Wireshark

## Steps
1. Download & Install Wireshark
2. Capture all packages when you access http://www.zju.edu.cn (using filter)
3. Using Wireshark to analyze the packets
4. Write a report (in PDF) to describe the procedure & results of the capture & analysis process

## Before Reading
- **Most result of capturing has been converted to YAML formant to enhance human readability.**  

## Install Wireshark

Since I use Ubuntu, I can simply get Wireshark by:  

```shell
$ sudo apt install wireshark
```

And it's done.  

## Capture Packages

Just start capturing, and visit http://www.zju.edu.cn via browser. Stop capturing after the web page has been loaded completely.  

### Finding the IP address
It's obvious that we've captures quite a lot of packages in less than fifteen seconds. That's alright, let's start from looking up DNS request, by setting filter to `dns`. The reason I do this is that I need to know the IP address of ZJU homepage, and then I can use filter to show the packages from/to this IP only.  

```yaml
# Packet 4 from /tmp/wireshark_wlo19JCQ10.pcapng
- 43
- 2021-04-16 16:05:38.891169453
- 10.185.27.14
- 10.10.0.21
- DNS
- 85
- Standard query 0x4e26 A www.zju.edu.cn OPT
```

This is a DNS standard query. It's easy to find the corresponding response:  

```yaml
# Packet 6 from /tmp/wireshark_wlo19JCQ10.pcapng
- 45
- 2021-04-16 16:05:38.914106481
- 10.10.0.21
- 10.185.27.14
- DNS
- 101
- Standard query response 0x4e26 A www.zju.edu.cn A 10.203.6.122 OPT
```

This DNS standard query request tells us, that www.zju.edu.cn is an *class A domain name*, and the IP address of it is `10.203.6.122`. Obviously, this IP address is under `10.0.0.0/8`, which means it is a private IP address.  

Now, lets change the filter to `ip.addr == 10.203.6.122`. Press `ENTER` and, ohhh!  Let's go!  

![after_filter_zju](./after_filter_zju.png)


### Analyzing

#### TCP handshake
Quite a lot of things have happened during that fifteen seconds.  
Firstly, let's look at these three packages:  

```yaml
# Packet 0 from /tmp/wireshark_wlo19JCQ10.pcapng
- 47
- 2021-04-16 16:05:38.915527118
- 10.185.27.14
- 10.203.6.122
- TCP
- 74
- 39500 → 80 [SYN] Seq=0 Win=64240 Len=0 MSS=1460 SACK_PERM=1 TSval=2582007217 TSecr=0 WS=128
---
# Packet 1 from /tmp/wireshark_wlo19JCQ10.pcapng
- 48
- 2021-04-16 16:05:38.921543688
- 10.203.6.122
- 10.185.27.14
- TCP
- 74
- 80 → 39500 [SYN, ACK] Seq=0 Ack=1 Win=28960 Len=0 MSS=1460 SACK_PERM=1 TSval=4276858962 TSecr=2582007217 WS=128
---
# Packet 2 from /tmp/wireshark_wlo19JCQ10.pcapng
- 49
- 2021-04-16 16:05:38.921577173
- 10.185.27.14
- 10.203.6.122
- TCP
- 66
- 39500 → 80 [ACK] Seq=1 Ack=1 Win=64256 Len=0 TSval=2582007223 TSecr=4276858962
```

These are the first three packages related to `10.203.6.122`. This is a typical TCP handshake procedure.  
This is a HTTP request without TLS, so my device try to send request to `10.203.6.122:80`, and set the synchronization bit `SYN=1`. After `6 ms`, my device received a TCP package from `10.203.6.122:80`, with acknowledgment bit `ACK=1` set alongside with `SYN=1`. My device send another package to the server in less than `0.03 ms`, setting `ACK=1`.  

#### HTTP request and response

Let's inspect some HTTP packages. Here is one:  

```yaml
# Packet 3 from /tmp/wireshark_wlo19JCQ10.pcapng
- 50
- 2021-04-16 16:05:38.921700196
- 10.185.27.14
- 10.203.6.122
- HTTP
- 2742
- GET / HTTP/1.1 
```

This is a HTTP request. The request-line of this HTTP request is `GET / HTTP/1.1`. This tells us three important things:  
1. This HTTP request uses GET method.  
2. It tries to request the resource under the root `/` directory.  
3. It uses HTTP/1.1 protocol.  

HTTP/1.1 is a plain-text protocol. Unlike HTTP/2, we can read raw HTTP/1.1 easily, since it contains ASCII characters.  
We can see the terminating characters in HTTP/1.1, which are `0D 0A`. We can find it easily at the end of request-line:  

```
0040   b0 52 47 45 54 20 2f 20 48 54 54 50 2f 31 2e 31   .RGET / HTTP/1.1
0050   0d 0a 48 6f 73 74 3a 20 77 77 77 2e 7a 6a 75 2e   ..Host: www.zju.
0060   65 64 75 2e 63 6e 0d 0a 55 73 65 72 2d 41 67 65   edu.cn..User-Age
```

The corresponding HTTP response is:  

```yaml
# Packet 8 from /tmp/wireshark_wlo19JCQ10.pcapng
- 55
- 2021-04-16 16:05:38.935540041
- 10.203.6.122
- 10.185.27.14
- HTTP
- 5015
- HTTP/1.1 200 OK  (text/html)
```

It shows the status code `200`, which means `OK`. It also shows the MIME type of this response, which is `text/html`.  
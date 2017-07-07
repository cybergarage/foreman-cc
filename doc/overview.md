# OVERVIEW

## What is Foreman ?

Foreman is an open-source framework for monitoring, analysis and alerting for cloud computing.

## Features

Foreman's main features are:

- a federated time series database system
- an automated QoS and failure detector

## Architecture

This diagram illustrates the core architecture of Foreman, and the core components are written in C.

![Foreman System Architecture](img/forman_system_block.svg)

### Federated database

A federated database system is a type of database system, which consists of multiple autonomous database systems into a single federated database. Foreman is the primitive database; the operator can define a federated database system which consists of multiple Foremans.

The interface of the time series database is abstracted for the federated database; Foreman is an implementation of the abstract interface. Through the interface abstraction, the consumer and the provider can access the federated database system with a uniform method.

### Message Passing

A Foreman instance is an object that can send and receive messages with other Foreman instances like the actor model. Foreman supports a publish/subscribe model to chain multiple RingMap instances hierarchically and dynamically. Each Foreman instance has a unique identier consisting of host and name, and a Foreman instance can subscribe to other RingMap instances. The following figure shows each Foreman instance sends a message to other Foreman instances.

![Foreman Actor Model](img/forman_actor_model.svg)

Using the message passing functionality, the consumer and provider can create tiered time series databases with any aggregations and different intervals more hierarchically and effectively. For example, The following figure shows three RingMap instances with di erent intervals, every minute, hourly, and daily. The RingMap instances are updated from a metrics data source hierarchically.

![Federated Example](img/forman_tiered_example.svg)

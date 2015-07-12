#!/usr/bin/env bash

diff test.expected <(./gurls < test.input)
